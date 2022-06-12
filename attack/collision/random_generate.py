import random
import string


ROUND = 10000
ALLOWED_CHARS = string.ascii_letters + string.digits
y = [ord(x) for x in ALLOWED_CHARS]
y.sort()
print(y)
random.seed(4)


    
    
