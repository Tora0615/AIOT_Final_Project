from flask import Flask, render_template, request
import numpy as np
import pandas as pd
import joblib


app = Flask(__name__)

names = [
    'aluminium',
    'ammonia',
    'arsenic',
    'barium',
    'cadmium',
    'chloramine',
    'chromium',
    'copper',
    'flouride',
    'bacteria',
    'viruses',
    'lead',
    'nitrates',
    'nitrites',
    'mercury',
    'perchlorate',
    'radium',
    'selenium',
    'silver',
    'uranium'
]

def modelpredict(input):
    df = pd.DataFrame([input], columns=names)
    loaded_model = joblib.load('water_model')
    predict = loaded_model.predict(df)
    return predict

'''
# mode
  auto: 0
  manual: 1

# switch
  close: 0
  open: 1
'''
@app.route('/input')
def input_page():
    f = open('open_flag', 'r')
    flags = [ flag.strip() for flag in f.readlines()]
    f.close()
    mode = 'auto'
    if flags[0][0] == '1':
        mode = 'manual'
    open_close = 'close'
    if flags[1][0] == '1':
        open_close = 'open'
    return render_template('input.html', names=names, mode=mode, open_close=open_close,
                           open_close_inverse='open' if open_close == 'close' else 'close')


@app.route('/input-respond')
def input_respond():
    values = np.array([float(request.values.get(name)) for name in names])
    outcome = 'safe' if modelpredict(values) == 1 else 'unsafe'
    if mode_flag() == 'auto':
        f = open('open_flag', 'r')
        flags = [flag for flag in f.readlines()]
        f.close()
        flags[1] = ('0' if outcome == 'unsafe' else '1') + flags[1][1:]
        f = open('open_flag', 'w')
        f.writelines(flags)
        f.close()
    return outcome

@app.route('/mode-flag')
def mode_flag():
    f = open('open_flag', 'r')
    flags = [flag.strip() for flag in f.readlines()]
    f.close()
    return 'auto' if flags[0][0] == '0' else 'manual'

@app.route('/mode-switch')
def mode_switch():
    f = open('open_flag', 'r')
    flags = [flag for flag in f.readlines()]
    f.close()
    flags[0] = ('1' if flags[0][0] == '0' else '0') + flags[0][1:]
    f = open('open_flag', 'w')
    f.writelines(flags)
    f.close()
    return 'auto' if flags[0][0] == '0' else 'manual'

@app.route('/switch-flag')
def switch_flag():
    f = open('open_flag', 'r')
    flags = [flag for flag in f.readlines()]
    f.close()
    return 'close' if flags[1][0] == '0' else 'open'

@app.route('/switch-switch')
def switch_switch():
    outcome = 'None'
    if mode_flag() == 'manual':
        f = open('open_flag', 'r')
        flags = [flag for flag in f.readlines()]
        f.close()
        flags[1] = ('1' if flags[1][0] == '0' else '0') + flags[1][1:]
        f = open('open_flag', 'w')
        f.writelines(flags)
        f.close()
        outcome = 'close' if flags[1][0] == '0' else 'open'
    return outcome


@app.route('/aiot')
def aiot_open():  # put application's code here
    if switch_flag() == 'open':
        return "true"
    else:
        return "false"


if __name__ == '__main__':
    app.run(host="0.0.0.0",port=5000)
