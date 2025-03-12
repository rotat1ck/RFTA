from flask import Blueprint, request, jsonify
from app.models import Server, db

servers_bp = Blueprint('servers', __name__)

# @servers_bp.route('/', methods=['GET'])
# def list_servers():
#     servers = Server.query.all()
#     return jsonify([{"id": server.id, "name": server.name, "status": server.status} for server in servers]), 200

# @servers_bp.route('/', methods=['POST'])
# def create_server():
#     data = request.get_json()
#     name = data.get('name')
#     status = data.get('status', 'stopped')  # Default status

#     if not name:
#         return jsonify({"error": "Server name is required"}), 400

#     new_server = Server(name=name, status=status)
#     db.session.add(new_server)
#     db.session.commit()

#     return jsonify({"message": "Server created successfully", "id": new_server.id}), 201