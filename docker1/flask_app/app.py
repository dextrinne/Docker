from flask import Flask, jsonify
from models import db, User

app = Flask(__name__)

# Настройка подключения к базе данных PostgreSQL в Docker
app.config['SQLALCHEMY_DATABASE_URI'] = 'postgresql://user:password@db:5432/mydatabase'
app.config['SQLALCHEMY_TRACK_MODIFICATIONS'] = False
db.init_app(app)

with app.app_context():
    db.create_all()

@app.route('/flask')
def hello():
    return "Hello!"

@app.route('/users', methods=['GET'])
def get_users():
    users = User.query.all()
    return jsonify([{'id': user.id, 'name': user.name} for user in users])

if __name__ == '__main__':
    app.run(host='0.0.0.0', debug=True)
