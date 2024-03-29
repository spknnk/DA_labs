import sys
import random
import string

def get_random_key():
    return random.choice( string.ascii_letters )

if __name__ == "__main__":
    # Проверяем, что передали 1 аргумент.
    if len(sys.argv) != 2:
        print( "Usage: {0} <count of tests>".format( sys.argv[0] ) )
        sys.exit(1)
    
    count_of_tests = int( sys.argv[1] )

    actions = [ "+", "-" ]

    for enum in range( count_of_tests ):
        keys = dict()
        test_file_name = "tests/{:02d}".format( enum + 1 )
        with open( "{0}.t".format( test_file_name ), 'w' ) as output_file, \
             open( "{0}.a".format( test_file_name ), "w" ) as answer_file:

            for _ in range( random.randint(100000, 1000000) ):
                action = random.choice( actions )
                if action == "+":
                    key = get_random_key()
                    value = random.randint( 1, 100 )
                    output_file.write("+ {0} {1}\n".format( key, value ))
                    key = key.lower()
                    # Если в нашем словаре уже есть такой ключ, то ответе должно быть 
                    # сказано, что он существует, иначе --- успешное добавление.
                    answer = "Exist"
                    if key not in keys:
                        answer = "OK"
                        keys[key] = value
                    answer_file.write( "{0}\n".format( answer ) )

                elif action == "-":
                    key = get_random_key()
                    output_file.write("- {0}\n".format( key ))

                    if key in keys:
                        answer = "OK: {0}".format( keys[key] )
                    else:
                        answer = "NoSuchWord"
                    answer_file.write( "{0}\n".format( answer ) )