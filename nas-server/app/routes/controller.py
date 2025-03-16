from flask import Blueprint, jsonify, request
from app.models import User, Server, db
from app.utils.jwtdec import token_required

controller_bp = Blueprint('controller', __name__)

@controller_bp.route('/startserver/<int:serverId>', methods=['POST'])
@token_required
def start_server(user, serverId):
    server = Server.query.get(serverId)
    if user.role < 2:
        return jsonify({'message': 'You do not have permission to start this server'}), 403
    
    if server is None:
        return jsonify({"error": "Server not found"}), 404

    # TODO: add code to start the server ;)
    server.status = True
    db.session.commit()

    return jsonify({"message": "Server started"}), 200

@controller_bp.route('/stopserver/<int:serverId>', methods=['POST'])
def stop_server(user, serverId):
    server = Server.query.get(serverId)
    if user.role < 3:
        return jsonify({'message': 'You do not have permission to stop this server'}), 403
    
    if server is None:
        return jsonify({"error": "Server not found"}), 404

    # TODO: add code to stop the server ;)
    server.status = False
    db.session.commit()

    return jsonify({"message": "Server stopped"}), 200