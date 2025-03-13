from flask import Blueprint, jsonify
from app.models import Server, db

controller_bp = Blueprint('controller', __name__)

# @controller_bp.route('/<int:server_id>/start', methods=['POST'])
# def start_server(server_id):
#     server = Server.query.get(server_id)
#     if server is None:
#         return jsonify({"error": "Server not found"}), 404

#     server.status = 'running'
#     db.session.commit()

#     return jsonify({"message": f"Server {server.name} started successfully"}), 200

# @controller_bp.route('/<int:server_id>/stop', methods=['POST'])
# def stop_server(server_id):
#     server = Server.query.get(server_id)
#     if server is None:
#         return jsonify({"error": "Server not found"}), 404

#     server.status = 'stopped'
#     db.session.commit()

#     return jsonify({"message": f"Server {server.name} stopped successfully"}), 200