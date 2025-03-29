from app.models import User

lvlTwoRestrictions  =  ['start', 'stop', 
                        'ban', 'pardon', 'ban-ip', 'pardon-ip', 
                        'op', 'deop', 
                        'execute', 'give', 'gamemode', 'gamerule']

lvlThreeRestrictions = ['stop', 
                        'ban-ip', 'pardon-ip', 
                        'op', 'deop', 
                        'execute', 'give', 'gamemode']

lvlFourRestrictions  = ['op', 'deop',
                        'execute', 'give']

def getRestrictions(user):
    match user.role:
        case 2:
            return lvlTwoRestrictions
        case 3:
            return lvlThreeRestrictions
        case 4:
            return lvlFourRestrictions
        case 5:
            return []
        case _:
            return lvlTwoRestrictions
        
def checkPermissions(user, command):
    restrictions = getRestrictions(user)
    
    for i in restrictions:
        if i in command:
            return False
        
    return True