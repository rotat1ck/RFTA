from flask import Blueprint, request, jsonify, current_app
from app.models import Server, User, db
from app.utils.jwtdec import token_required
import os

servers_bp = Blueprint('servers', __name__)

@servers_bp.route('/', methods=['GET'])
@token_required
def listServers(currentUser):
    servers = Server.query.all()
    return jsonify([{"id": server.id, "name": server.name, "status": server.status, "version": server.version, 
                    "core": server.core} for server in servers]), 200

@servers_bp.route("/addserver", methods=['POST'])
@token_required
def createServer(user):
    if (user.role < 4):
        return jsonify({"error": "You don't have permission to create a server"}), 403
    
    name = request.args.get('name')
    if name is None:
        return jsonify({"error": "Server name is required"}), 400
    
    if Server.query.filter_by(name=name).first():
        return jsonify({"error": "Server with this name already exists"}), 400
    
    if len(name) < 3 or len(name) > 10:
        return jsonify({"error": "Server name must be between 3 and 10 characters"}), 400
    
    servers = Server.query.all()
    if len(servers) >= 5:
        return jsonify({"error": "Maximum number of servers reached"}), 400
    
    new = Server(name=name, status=False)
    db.session.add(new)
    db.session.commit()

    serverDir = os.path.join(current_app.config['SERVERS_URI'], new.name)
    if not os.path.exists(serverDir):
        os.makedirs(serverDir)

    return jsonify({"message": "Server created successfully"}), 200

@servers_bp.route("/deleteserver/<int:serverId>", methods=['DELETE'])
@token_required
def deleteServer(user, serverId):
    if (user.role < 4):
        return jsonify({"error": "You don't have permission to delete a server"}), 403
    
    server = Server.query.filter_by(id=serverId).first()
    if server is None:
        return jsonify({"error": "Server not found"}), 404
    
    db.session.delete(server)
    db.session.commit()
    return jsonify({"message": "Server deleted successfully"}), 200
    

@servers_bp.route("/changeversion/<int:serverId>", methods=['POST'])
@token_required
def changeVersion(user, serverId):
    if user.role < 4:
        return jsonify({"error": "You don't have permission to change the server version"}), 403
    
    newVersion = request.args.get("version")
    if newVersion is None:
        return jsonify({"error": "Server version is required"}), 400
    
    if len(newVersion) < 5 or len(newVersion) > 25:
        return jsonify({"error": "Server version must be between 5 and 30 characters"}), 400
    
    server = Server.query.filter_by(id=serverId).first()
    
    if server is None:
        return jsonify({"error": "Server not found"}), 404
    
    server.version = newVersion
    db.session.commit()
    
    return jsonify({"message": "Server version changed successfully"}), 200

@servers_bp.route("/changecore/<int:serverId>", methods=['POST'])
@token_required
def changeCore(user, serverId):
    if user.role < 4:
        return jsonify({"error": "You don't have permission to change the server core"}), 403
    
    newCore = request.args.get("core")
    if newCore is None:
        return jsonify({"error": "Server core is required"}), 400
    
    if len(newCore) < 5 or len(newCore) > 25:
        return jsonify({"error": "Server core must be between 5 and 30 characters"}), 400
    
    server = Server.query.filter_by(id=serverId).first()
    
    if server is None:
        return jsonify({"error": "Server not found"}), 404
    
    server.core = newCore
    db.session.commit()
    
    return jsonify({"message": "Server core changed successfully"}), 200

@servers_bp.route("/getmp/<int:serverId>", methods=['GET'])
@token_required
def getMp(currentUser, serverId):
    return jsonify({"message": "This endpoint is not implemented yet"}), 501

@servers_bp.route("/loadjar/<int:serverId>", methods=['POST'])
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

    serverDir = os.path.join(current_app.config['SERVERS_URI'], server.name)
    modsDir = os.path.join(serverDir, 'mods')
    if not os.path.exists(modsDir):
        os.makedirs(modsDir)

    filePath = os.path.join(modsDir, file.filename)
    file.save(filePath)

    return jsonify({"message": "Mod loaded successfully"}), 200

@servers_bp.route("/loadzip/<int:serverId>", methods=['POST'])
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

    serverDir = os.path.join(current_app.config['SERVERS_URI'], server.name)
    modsDir = os.path.join(serverDir, 'mods')
    if not os.path.exists(modsDir):
        os.makedirs(modsDir)

    filePath = os.path.join(modsDir, file.filename)
    file.save(filePath)

    # TODO: Unzip the file from folder

    return jsonify({"message": "Archive loaded successfully"}), 200