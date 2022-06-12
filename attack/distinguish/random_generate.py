import random
import string


ROUND = 10000
ALLOWED_CHARS = string.ascii_letters + string.digits
random.seed(4)
for _ in range(ROUND):
    str_size = random.randint(10, 1000)
    output = ''.join(random.choice(ALLOWED_CHARS) for _ in range(str_size))
    print(output)
    # 随机修改output中的1bit
    # the first bit of ascii is always 0
    while True:
        pos = random.randint(0, str_size - 1)
        pos_8 = random.randint(0, 6)
        tmp = ord(output[pos])
        tmp ^= (1 << pos_8)
        if ALLOWED_CHARS.find(chr(tmp)) != -1:
            break
    output2 = output[0:pos] + chr(tmp) + output[pos+1: str_size]
    print(output2)

    
    
