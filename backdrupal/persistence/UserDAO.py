from backdrupal import database

class UserDAO:
    def insertUserDAO(self, user):
        database.session.add(user)
        if database.session.commit() == None:
            return True
        return False

    def deleteUserDAO(self, user):
        database.session.delete(user)
        if database.session.commit() == None:
            return True
        return False