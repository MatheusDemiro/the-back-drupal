from flask import Flask
from flask_sqlalchemy import SQLAlchemy
import settings

app = Flask(__name__)
app.config.from_object(settings)

database = SQLAlchemy(app)

from backdrupal.routes import UserRoutes