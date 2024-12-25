from app import app, db, User

# Функция для инициализации базы данных
def init_db():
    with app.app_context():
        db.create_all()  # Создание таблиц

        # Если в базе данных нет пользователей, добавляем тестового пользователя
        if not User.query.filter_by(name='testuser').first():
            test_user = User(name='testuser')
            db.session.add(test_user)
            db.session.commit()

# Запускаем инициализацию базы данных
if __name__ == '__main__':
    init_db()

