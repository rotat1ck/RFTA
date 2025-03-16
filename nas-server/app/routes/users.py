from flask import Blueprint, request, jsonify
from app.models import User, db
from app.utils.jwtdec import token_required, create_token

users_bp = Blueprint('users', __name__)

@users_bp.route('/login', methods=['GET'])
def loginUser():
    username = request.args.get('username')
    password = request.args.get('pass')
    if not username or not password:
        return jsonify({"error": "Username and password are required"}), 400

    user = User.query.filter_by(username=username).first()
    if user is None or user.hash != password:
        return jsonify({"error": "Invalid username or password"}), 401
    
    if user.banned:
        return jsonify({"error": "User is banned"}), 403

    return jsonify({
        "token": create_token(user.username),
        "role": user.role,
    }), 200
    
@users_bp.route('/changepass', methods=['GET'])
@token_required
def logoutUser(user):
    newpass = request.args.get('pass')
    
    if newpass is None:
        return jsonify({"error": "New password is required"}), 400
    
    if len(newpass) != 64:
        return jsonify({"error": "Only hash is allowed;)"}), 400
    
    if user is None:
        return jsonify({"error": "User not found"}), 404
    
    user.hash = newpass
    db.session.commit()
    return jsonify({"message": "Password changed successfully"}), 200