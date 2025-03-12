from flask import Blueprint, request, jsonify
from app.models import User, db

users_bp = Blueprint('users', __name__)

# @users_bp.route('/', methods=['POST'])
# def register_user():
#     data = request.get_json()
#     username = data.get('username')
#     password = data.get('password')

#     if not username or not password:
#         return jsonify({"error": "Username and password are required"}), 400

#     new_user = User(username=username, password=password)
#     db.session.add(new_user)
#     db.session.commit()

#     return jsonify({"message": "User  registered successfully"}), 201

@users_bp.route('/login', methods=['GET'])
def login_user():
    # data = request.get_json()
    # username = data.get('username')
    # password = data.get('password')
    # if not username or not password:
    #     return jsonify({"error": "Username and password are required"}), 400

    return jsonify({"message": "User logged in successfully"}), 200

@users_bp.route('/<int:user_id>', methods=['GET'])
def get_user(user_id):
    user = User.query.get(user_id)
    if user is None:
        return jsonify({"error": "User  not found"}), 404

    return jsonify({"id": user.id, "username": user.username}), 200