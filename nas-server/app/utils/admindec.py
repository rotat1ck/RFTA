from flask import current_app, request, jsonify
import jwt
from functools import wraps
from app.models import User

def admin_only(f):
    @wraps(f)
    def decorated(*args, **kwargs):
        token = None
        if 'Authorization' in request.headers:
            token = request.headers['Authorization'].split()[1]

        if not token:
            return jsonify({'error': 'Token is missing'}), 401

        try:
            data = jwt.decode(token, current_app.config['SECRET_KEY'], algorithms=['HS256'])
            current_user = data['sub']
        except jwt.ExpiredSignatureError:
            return jsonify({'error': 'Expired token'}), 401
        except jwt.InvalidTokenError:
            return jsonify({'error': 'Invalid token'}), 401

        admin = User.query.filter_by(username=current_user).first()
        if admin is None or admin.role != 5:
            return jsonify({'error': 'Nice try'}), 403
        
        return f(current_user, *args, **kwargs)

    return decorated