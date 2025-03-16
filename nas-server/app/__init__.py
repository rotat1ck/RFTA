from flask import Flask
from .config import initConfig
from .routes.users import users_bp
from .routes.servers import servers_bp
from .routes.controller import controller_bp
from .routes.admin import admin_bp

def startApp():
    app = Flask(__name__)
    initConfig(app)

    app.register_blueprint(users_bp, url_prefix='/api/users')
    app.register_blueprint(servers_bp, url_prefix='/api/servers')
    app.register_blueprint(controller_bp, url_prefix='/api/controller')
    app.register_blueprint(admin_bp, url_prefix='/api/admin')

    return app