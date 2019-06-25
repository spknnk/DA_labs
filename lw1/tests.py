import random
import string

MAX_KEY_VALUE = 16**32 - 1
MAX_VALUE_LEN = 64

def generate_random_value():
    return "".join( [ random.choice(string.ascii_letters  + string.digits) for _ in range(0, random.randint(1, MAX_VALUE_LEN)) ] )

if __name__ == "__main__":
    for num in range(1, 2):
        values = list()
        output_filename = "t{:02d}.t".format( num )
        with open( output_filename, 'w') as output:
            for _ in range(1, 10):
                key = random.randint(16**31, MAX_KEY_VALUE)
                key = hex(key).split('x')[-1]
                value = generate_random_value()
                values.append( (key, value) )
                output.write( "{}\t{}\n".format(key, value) )
        # Answer.
        # values[0][0] -- key
        # values[0][1] -- value
        output_filename = "t{:02d}.a".format( num )
        with open( output_filename, 'w') as output:
            values = sorted( values, key=lambda x: x[0] )
            for value in values:
                output.write( "{}\t{}\n".format(value[0], value[1]) )