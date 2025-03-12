from .db import db

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    hash = db.Column(db.String(120), nullable=False)
    role = db.Column(db.Integer, nullable=False)
    sessionId = db.Column(db.String(120), nullable=False)
    expires = db.Column(db.Date, nullable=False)

class Server(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(80), unique=True, nullable=False)
    status = db.Column(db.String(20), nullable=False)
    