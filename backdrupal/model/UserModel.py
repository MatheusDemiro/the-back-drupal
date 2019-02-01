from backdrupal import database
from marshmallow import Schema, fields

class User(database.Model):
    __tablename__ = 'user'

    id = database.Column(database.Integer, primary_key=True, autoincrement=True, nullable=False)
    name = database.Column(database.String(40))
    email = database.Column(database.String(50), unique=True)
    type = database.Column(database.String(9))
    password = database.Column(database.String(64))

    def __init__(self, name, email, type, password):
        self.name = name
        self.email = email
        self.type = type
        self.password = password

class UserSchema(Schema):
    id = fields.Integer(allow_none=True)
    email = fields.Str()
    name = fields.Str()
    type = fields.Str()
    password = fields.Str()
    disabled = fields.Integer()
