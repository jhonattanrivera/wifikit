function getRelayStatus(n) {
  $.get('status?relay=' + n, function(response) {
    if (response.status == 1){
      $('#rele-' + n).addClass('is-checked')
    }
  });
}

function switchRelayOn(n) {
  $.get('on?relay=' + n, function(response) {
    if (response.status == 1){
      $('#rele-' + n).addClass('is-checked')
    }
  });
}

function switchRelayOff(n) {
  $.get('off?relay=' + n, function(response) {
    if (response.status == 0){
      $('#reley-' + n).removeClass('is-checked')
    }
  });
}


$(document).ready(function() {
  $('body').html('<div class="mdl-layout mdl-js-layout mdl-layout--fixed-header"><header class="mdl-layout__header"><div class="mdl-layout__header-row"><span class="mdl-layout-title">Panel</span></div></header><div class="mdl-layout__drawer"><pan class="mdl-layout-title">Panel</span></div><main class="mdl-layout__content"><div class="page-content"><div id="contenedor" class="demo-content mdl-color--white mdl-shadow--4dp content mdl-color-text--grey-800 mdl-cell mdl-cell--8-col"><div id="descripcion"><p>Con esta aplicación web puede manejarse ambos relés del dispositivo sin necesidad de un servidor, es el ESP8266 quien ofrece los contenidos. Es necesario que el dispositivo tenga acceso a internet ya que el contenido es remoto dada la limitación de la memoria flash del dispositivo</p></div><div class="rele"><h3>Relay1</h3><div class="mando"><label id="rele-1" class="mdl-switch mdl-js-switch mdl-js-ripple-effect" for="switch-1"><input type="checkbox" id="switch-1" class="mdl-switch__input"></label></div></div><div class="rele"><h3>Relay2</h3><div class="mando"><label id="rele-2" class="mdl-switch mdl-js-switch mdl-js-ripple-effect" for="switch-2"><input type="checkbox" id="switch-2" class="mdl-switch__input"></label></div></div></div></main></div>');
  getRelayStatus(1);
  getRelayStatus(2);
  
  $('#switch-1').click(function(){
    if($('#switch-1').parent().hasClass('is-checked')){
      switchRelayOff(1);
    }
    else {
      switchRelayOn(1);
    }
  });

  $('#switch-2').click(function(){
    if($('#switch-2').parent().hasClass('is-checked')){
      switchRelayOff(2);
    }
    else {
      switchRelayOn(2);
    }
  });
});


