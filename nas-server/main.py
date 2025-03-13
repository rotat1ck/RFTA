from app import startApp
from app.db import db

app = startApp()

with app.app_context():
    db.create_all()

if __name__ == '__main__':
    app.run(debug=True)