from app import startApp
from app.db import db
from os import path

app = startApp()

with app.app_context():
    db.create_all()
    
current_dir = path.dirname(path.abspath(__file__))
cert_file = path.join(current_dir, 'secret/cert.pem')
key_file = path.join(current_dir, 'secret/key.pem')

if __name__ == '__main__':
    app.run(ssl_context=(cert_file, key_file), host='0.0.0.0', port=7777, debug=True)