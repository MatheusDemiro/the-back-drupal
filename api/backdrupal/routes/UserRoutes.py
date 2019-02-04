from backdrupal.Facade import request, jsonify, abort, make_response, app, Facade
from flask_cors import CORS

from backdrupal.model.UserModel import User, UserSchema

#Permissoes CORS - permitir que qualquer dominio acesse a API.
CORS(app)

facade = Facade()

@app.route('/api/users', methods=['POST', 'GET'])
def users():
    search = request.args.get('q')
    if request.method == "POST":
        result = facade.insertUser(User(**UserSchema().load(request.get_json()).data))
        if result['sucess']:
            return jsonify(result), 200
        return abort(make_response(jsonify(result), 400))
    if request.method == "GET":
        if search == None:
            result = facade.getAllUsers()
            if result['sucess']:
                return jsonify(result), 200
            return abort(make_response(jsonify(result), 404))
        else:
            result = facade.searchUser(search)
            result['data'] = UserSchema(many=True).dump(result['data']).data
            if result['sucess']:
                return jsonify(result), 200
            return abort(make_response(jsonify(result), 404))

@app.route('/api/users/<int:user_id>', methods=['DELETE'])
def deleteUser(user_id):
    if request.method == "DELETE":
        result = facade.deleteUser(user_id)
        if result:
            return jsonify(result), 200
        return abort(make_response(jsonify(result), 400))

