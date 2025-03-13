from flask import Blueprint, request, jsonify
from app.models import User
from app.utils.admindec import admin_only

admin_bp = Blueprint('admin', __name__)

@admin_bp.route('/getuser/<int:user_id>', methods=['GET'])
@admin_only
def getUser(requesterUsername, user_id):
    user = User.query.get(user_id)
    if user is None:
        return jsonify({"error": "User  not found"}), 404

    return jsonify({"id": user.id, "username": user.username}), 200

@admin_bp.route('/createuser', methods=['GET'])
@admin_only
def createUser(requesterUsername):
    admin = User.query.filter_by(username=requesterUsername).first()
    if admin is None or admin.role != 5:
        return jsonify({'error': 'Nice try'}), 403
    