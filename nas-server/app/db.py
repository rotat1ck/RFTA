from flask_sqlalchemy import SQLAlchemy
from os import getenv
from dotenv import load_dotenv

load_dotenv() 
db = SQLAlchemy()

def init_db(app):
    app.config['SQLALCHEMY_DATABASE_URI'] = getenv("DB_URI")
    app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
    db.init_app(app)