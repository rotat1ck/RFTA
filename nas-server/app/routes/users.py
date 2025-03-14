from flask import Blueprint, request, jsonify
from app.models import User, db
from app.utils.jwtdec import token_required, create_token

users_bp = Blueprint('users', __name__)

# @users_bp.route('/', methods=['POST'])
# def register_user():
#     data = request.get_json()
#     username = data.get('username')
#     password = data.get('pass')

#     if not username or not password:
#         return jsonify({"error": "Username and password are required"}), 400

#     new_user = User(username=username, password=password)
#     db.session.add(new_user)
#     db.session.commit()

#     return jsonify({"message": "User  registered successfully"}), 201

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