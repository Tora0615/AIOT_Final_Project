var float_re = new RegExp('^[0-9]+.?[0-9]*$');

function input() {
    let names = [
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
    var re_pass = 1;
    var values = ''
    for (var i = 0; i < 20; i++) {
        if(!float_re.test($(`#${names[i]}`).val())) {
            $("#outcome").val(`${names[i]} 格式錯誤`);
            re_pass = 0;
            break;
        }
        values += (names[i] + "=" + $(`#${names[i]}`).val() + "&");
    }

    if(re_pass) {
        const xhttp = new XMLHttpRequest();
        xhttp.onload = function() {
            document.getElementById("outcome").value = this.responseText;
            const yhttp = new XMLHttpRequest();
            yhttp.onload = function () {
                $("#open_close").text(`switch: ${this.responseText}`);
                if(this.responseText == "open") {
                    $("#open_close_button").text("close");
                }
                else {
                    $("#open_close_button").text("open");
                }
            }
            yhttp.open("GET", "switch-flag");
            yhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
            yhttp.setRequestHeader("user-agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.88 Safari/537.36");
            yhttp.send();
        }

        xhttp.open("GET", `input-respond?${values}`);
        xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
        xhttp.setRequestHeader("user-agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.88 Safari/537.36");
        xhttp.send();
    }
}

function mode_switch() {
    const xhttp = new XMLHttpRequest();
    xhttp.onload = function() {
        $("#mode").text(`mode: ${this.responseText}`);
    }

    xhttp.open("GET", "mode-switch");
    xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhttp.setRequestHeader("user-agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.88 Safari/537.36");
    xhttp.send();
}

function open_close() {
    const xhttp = new XMLHttpRequest();
    xhttp.onload = function() {
        if(this.responseText != "None") {
            $("#open_close").text(`switch: ${this.responseText}`);
            if(this.responseText == "open") {
                $("#open_close_button").text("close");
            }
            else {
                $("#open_close_button").text("open");
            }
        }
    }

    xhttp.open("GET", `switch-switch`);
    xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhttp.setRequestHeader("user-agent", "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/100.0.4896.88 Safari/537.36");
    xhttp.send();
}