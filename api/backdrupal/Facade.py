from backdrupal.controllers import UserController
from flask import render_template, request, jsonify, make_response
from werkzeug.exceptions import abort
from backdrupal import app

class Facade:

    def __init__(self):
        self._user = UserController.UserController()

    def insertUser(self, user):
        return self._user.insertUser(user)

    def deleteUser(self, id):
        return self._user.deleteUser(id)

    def searchUser(self, name):
        return self._user.searchUser(name)

    def getAllUsers(self):
        return self._user.getAllUsers()
