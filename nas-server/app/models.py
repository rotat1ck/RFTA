from .config import db

class User(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    username = db.Column(db.String(80), unique=True, nullable=False)
    hash = db.Column(db.String(120), nullable=False)
    role = db.Column(db.Integer, nullable=False)
    banned = db.Column(db.Boolean, nullable=False, default=False)
    cooldown = db.Column(db.Integer, nullable=False, default=0)

class Server(db.Model):
    id = db.Column(db.Integer, primary_key=True)
    name = db.Column(db.String(80), unique=True, nullable=False)
    ip = db.Column(db.String(120), nullable=False)
    port = db.Column(db.Integer, nullable=False)
    foreign = db.Column(db.Boolean, nullable=False, default=False)
    status = db.Column(db.Boolean, nullable=False)
    version = db.Column(db.String(20), nullable=True)
    core = db.Column(db.String(20), nullable=True)
    
