from rcon.source import Client
from app.models import Server, User, db
from flask import current_app, jsonify
import os, time

def execute(user, server, command):
    if command[0] == '/':
        command = command[1:]
    
    if server.status == True:
        if 'dox' in command:
            return dox_player(server, command)
        elif 'light' in command:
            return light_player(server, command)
        elif 'start' in command:
            return start_server(user, server)
        else:
            if command == 'stop':
                if user.cooldown > time.time():
                    return jsonify({"message": f'You are on cooldown for {int(user.cooldown - time.time())} seconds'}), 400
                
            with Client(server.ip, server.port, passwd=current_app.config['RCON_KEY']) as client:
                if command == 'stop':
                    server.status = False
                    db.session.commit()
                    
                    user.cooldown = time.time() + 300
                    db.session.commit()
                    
                response = client.run(command)
                if response != "":
                    return response
                else:
                    return "Successfuly executed"
    else:
        if command == 'start':
            return start_server(user, server)
        
        return jsonify({"message": "Server is not running, use /start"}), 400
            
def start_server(user, server):
    if server.status == True:
        return jsonify({"message": "Server is already running"}), 400
    
    if server.foreign == True:
        return jsonify({"message": "Cannot start foreign server"}), 400
    
    if user.cooldown > time.time():
        return jsonify({"message": f'You are on cooldown for {int(user.cooldown - time.time())} seconds'}), 400

    try:
        serverDir = os.path.join(current_app.config['SERVERS_URI'], server.name.lower())
        os.chdir(serverDir)
        os.startfile("run.bat")
        
        server.status = True
        db.session.commit()
        
        user.cooldown = time.time() + 300
        db.session.commit()
        
        return 'Starting server'
    except Exception as e:
        return jsonify({"message": f'Failed to start server: {str(e)}'}), 400

def light_player(server, command):
    player_name = command[6:]
    with Client(server.ip, server.port, passwd=current_app.config['RCON_KEY']) as client:
        client.run(f'execute at {player_name} run summon minecraft:lightning_bolt ~ ~ ~')
    return "Successfuly executed"

def dox_player(server, command):
    player_name = command[4:]
    with Client(server.ip, server.port, passwd=current_app.config['RCON_KEY']) as client:
        client.run(f'effect give {player_name} minecraft:blindness 3 1 true')
        client.run(f'playsound minecraft:entity.ghast.scream ambient {player_name} ~ ~ ~ 10 0.5 1')
        client.run(f'title {player_name} times 0 40 0')
        client.run(f'title {player_name} subtitle {{\"text\":\"\u0418 \u0441\u043f\u043e\u0440\u0442\u0438\u043a\u043e\u0432\"}}')
        client.run(f'title {player_name} title {{\"text\":\"\u0416\u0434\u0438 \u0434\u043e\u043a\u0441. \u0441\u0432\u0430\u0442\"}}')
        client.run(f'playsound minecraft:entity.ghast.scream ambient {player_name} ~ ~ ~ 10 0.5 1')
        client.run(f'playsound minecraft:entity.ghast.scream ambient {player_name} ~ ~ ~ 10 0.5 1')
        client.run(f'playsound minecraft:entity.ghast.scream ambient {player_name} ~ ~ ~ 10 0.5 1')
    return "Successfuly executed"