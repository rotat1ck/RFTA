from flask import Blueprint, request, jsonify
from app.models import User, db
from app.utils.admindec import admin_only

admin_bp = Blueprint('admin', __name__)

@admin_bp.route('/getusers', methods=['GET'])
@admin_only
def getUsers(requesterUsername):
    users = User.query.all()
    return jsonify([{"id": user.id, "username": user.username, "role": user.role, "banned": user.banned} for user in users]), 200

@admin_bp.route('/getuser/<int:user_id>', methods=['GET'])
@admin_only
def getUser(requesterUsername, user_id):
    user = User.query.get(user_id)
    if user is None:
        return jsonify({"error": "User not found"}), 404

    return jsonify({"id": user.id, "username": user.username}), 200

@admin_bp.route('/createuser', methods=['POST'])
@admin_only
def createUser(requesterUsername):
    username = request.args.get('username')
    password = request.args.get('pass')
    role = request.args.get('role')
    if not username or not password or not role:
        return jsonify({"error": "Username, password and role are required"}), 400
    
    if User.query.filter_by(username=username).first() is not None:
        return jsonify({"error": "Username already exists"}), 400
    
    new = User(username=username, hash=password, role=role)
    db.session.add(new)
    db.session.commit()
    return jsonify({"message": "User registered successfully"}), 201

@admin_bp.route('/deleteuser/<int:user_id>', methods=['DELETE'])
@admin_only
def deleteUser(requesterUsername, user_id):
    user = User.query.get(user_id)
    if user is None:
        return jsonify({"error": "User not found"}), 404

    db.session.delete(user)
    db.session.commit()
    return jsonify({"message": "User deleted successfully"}), 200

@admin_bp.route('/banuser/<int:user_id>', methods=['POST'])
@admin_only
def banUser(requesterUsername, user_id):
    user = User.query.get(user_id)
    if user is None:
        return jsonify({"error": "User not found"}), 404
    
    if user.banned == True:
        return jsonify({"error": "User is already banned"}), 400
    
    user.banned = True
    db.session.commit()
    return jsonify({"message": "User banned successfully"}), 200

@admin_bp.route('/pardonuser/<int:user_id>', methods=['POST'])
@admin_only
def pardonUser(requesterUsername, user_id):
    user = User.query.get(user_id)
    if user is None:
        return jsonify({"error": "User not found"}), 404
    
    if user.banned == False:
        return jsonify({"error": "User is not banned"}), 400
    
    user.banned = False
    db.session.commit()
    return jsonify({"message": "User unbanned successfully"}), 200