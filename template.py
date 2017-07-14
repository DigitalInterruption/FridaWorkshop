import frida
import sys
def on_message(message, data):
            print message['payload']
 
jscode = """
"""
session = frida.attach("") 
script = session.create_script(jscode)
script.on('message', on_message)
script.load()
sys.stdin.read()


