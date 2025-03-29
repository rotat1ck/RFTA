from flask import Blueprint, jsonify, request, current_app
from app.models import Server, db
from app.utils.jwtdec import token_required
from app.utils.auth import checkPermissions
from app.utils.rconexec import execute, start_server
import os, zipfile

controller_bp = Blueprint('controller', __name__)

@controller_bp.route('/execute/<int:serverId>', methods=['POST'])
@token_required
def execute_command(user, serverId):
    server = Server.query.get(serverId)
    if server is None:
        return jsonify({"message": "Server not found"}), 404

    command = request.args.get('command')
    if command is None:
        return jsonify({"message": "Command is required"}), 400

    if not checkPermissions(user, command):
        return jsonify({"message": "You do not have permission to execute this command"}), 403
    
    result = execute(user, server, command)
    if isinstance(result, tuple) and result[0].is_json:
        return result
    
    return jsonify({"message": result}), 200

@controller_bp.route('/restartserver/<int:serverId>', methods=['POST'])
@token_required
def restart_server(user, serverId):
    server = Server.query.get(serverId)
    if server is None:
        return jsonify({"error": "Server not found"}), 404

    if not checkPermissions(user, 'stop'):
        return jsonify({"error": "You do not have permission to execute this command"}), 403
    
    if server.status == True:
        execute(user, server, 'stop')
        start_server(user, server)
    else:
        start_server(user, server)
        
    return jsonify({"message": "Server restarting"}), 200

@controller_bp.route("/loadjar/<int:serverId>", methods=['POST'])
@token_required
def loadJar(currentUser, serverId):
    if currentUser.role < 3:
        return jsonify({"error": "You don't have permission to load mods"}), 403
    
    file = request.files.get('mod')
    if file is None:
        return jsonify({"error": "Mod file is required"}), 400
    
    if not file.filename.endswith('.jar'):
        return jsonify({"error": "Only .jar files are allowed"}), 400
    
    server = Server.query.filter_by(id=serverId).first()
    
    if server is None:
        return jsonify({"error": "Server not found"}), 404

    serverDir = os.path.join(current_app.config['SERVERS_URI'], server.name.lower())
    modsDir = os.path.join(serverDir, 'mods')
    if not os.path.exists(modsDir):
        os.makedirs(modsDir)

    filePath = os.path.join(modsDir, file.filename)
    file.save(filePath)

    return jsonify({"message": "Mod loaded successfully"}), 200


@controller_bp.route("/loadzip/<int:serverId>", methods=['POST'])
@token_required
def loadZip(currentUser, serverId):
    if currentUser.role < 3:
        return jsonify({"error": "You don't have permission to load mods"}), 403
    
    file = request.files.get('zip')
    if file is None:
        return jsonify({"error": "Zip file is required"}), 400
    
    if not file.filename.endswith('.zip'):
        return jsonify({"error": "Only .zip files are allowed"}), 400
    
    server = Server.query.filter_by(id=serverId).first()
    
    if server is None:
        return jsonify({"error": "Server not found"}), 404

    serverDir = os.path.join(current_app.config['SERVERS_URI'], server.name.lower())
    modsDir = os.path.join(serverDir, 'mods')
    if not os.path.exists(modsDir):
        os.makedirs(modsDir)

    filePath = os.path.join(modsDir, file.filename)
    file.save(filePath)

    with zipfile.ZipFile(filePath, 'r') as zip_ref:
        zip_ref.extractall(modsDir)

    os.remove(filePath)

    return jsonify({"message": "Archive loaded successfully"}), 200