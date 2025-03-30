from app.models import User

lvlTwoRestrictions  =  ['start', 'stop', 'whitelist',
                        'ban', 'pardon', 'ban-ip', 'pardon-ip', 
                        'op', 'deop', 'tp', 'teleport', 'tpx', 'data', 'place',
                        'execute', 'give', 'gamemode', 'gamerule', 'item', 'replace', 'damage', 
                        'setblock', 'summon', 'effect', 'kill', 'attribute', 'defaultgamemode', 'clear'
                        'experience', 'xp', 'loot', 'enchant', 'fill', 'fillbiome', 'clone']

lvlThreeRestrictions = ['stop', 
                        'ban-ip', 'pardon-ip', 
                        'op', 'deop', 'tp', 'teleport', 'tpx', 'whitelist', 'data',
                        'execute', 'give', 'gamemode', 'item', 'replace', 'damage', 'place',
                        'setblock', 'summon', 'effect', 'kill', 'attribute', 'defaultgamemode', 'clear'
                        'experience', 'xp', 'loot', 'enchant', 'fill', 'fillbiome', 'clone']

lvlFourRestrictions  = ['op', 'deop',
                        'execute', 'give', 'item', 'replace', 'damage', 'data', 'place',
                        'setblock', 'summon', 'effect', 'attribute', 'defaultgamemode', 'clear'
                        'experience', 'xp', 'loot', 'enchant', 'fill', 'fillbiome','clone']

def getRestrictions(user):
    role = user.role

    if role == 2:
        return lvlTwoRestrictions
    elif role == 3:
        return lvlThreeRestrictions
    elif role == 4:
        return lvlFourRestrictions
    else:
        return []
        
def checkPermissions(user, command):
    restrictions = getRestrictions(user)
    command = command.replace('/', '')
    first = command.split(' ')[0]
    
    for i in restrictions:
        if i == first:
            return False
        
    return True