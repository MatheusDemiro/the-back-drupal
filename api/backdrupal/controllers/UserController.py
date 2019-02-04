from backdrupal.persistence import UserDAO
from backdrupal.model import UserModel

class UserController:
    def __init__(self):
        self._userDAO = UserDAO.UserDAO()
        self._userModel = UserModel.User

    def insertUser(self, user):
        validate = self.validateUser(user)
        if validate  == None:
            if self._userDAO.insertUserDAO(user):
                return {'sucess': True, 'message': "Usuário cadastrado com sucesso", 'statusCode': 200}
        return {'sucess': False, 'message': "Usuário já cadastrado", 'statusCode': 409}

    def deleteUser(self, id):
        verify = self._userModel.query.get(id)
        if verify:
            if self._userDAO.deleteUserDAO(verify):
                return {'sucess': True, 'message': "Usuário(s) deletado(s) com sucesso", 'statusCode': 200}
        return {'sucess': False, 'message': "Erro ao deletar usuário(s)", 'statusCode': 400}

    def searchUser(self, name):
        users = self._userModel.query.filter(self._userModel.name.like(name + "%")).all()
        if users:
            return {'sucess': True, 'data': users, 'statusCode': 200}
        return {'sucess': False, 'error': "Usuário não encontrado!" ,'statusCode': 404}

    def getAllUsers(self):
        users = self._userModel.query.all()
        if users:
            return {'sucess': True, 'data': users, 'statusCode': 200}
        return {'sucess': False, 'message': "Não há usuário(s) cadastrado(s) na base de dados.", 'statusCode': 404}

    def validateUser(self, user):
        if user.query.filter_by(email=user.email).first():
           return False
