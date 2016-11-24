var init = {lat: 37.772757, lng: -122.422596},omap, marker, markList=[], Bounds, carlist;
var url= '/location';

function initialize(){
  omap = new google.maps.Map(document.getElementById('map'), {
    zoom: 16,
    center: init
  });
  addMarker(init);
  omap.addListener('zoom_changed', function(){
    Bounds = omap.getBounds().toJSON();
    getCarData(function(){
      putTips()
    });
  })
  omap.addListener('tilesloaded', function(){
    Bounds = omap.getBounds().toJSON();
    getCarData(function(){
      putTips()
    });
  })

  function addMarker(location) {
    var marker = new google.maps.Marker({
      position: location,
      map: omap
    });
    markList.push(marker);
  }

  function getCarData(cb){
    if(!!omap){
      var data = [[Bounds.north,Bounds.east],[Bounds.south,Bounds.west]]
      $.get(url, {bounds: Bounds}, function(res){
        try {
          if(res.length != 0){
            for(var i=0; i< res.length; i++){
              if(res[i].location.coordinates.length != 0){
                carlist.push(res[i].location.coordinates)
              }
            }
            cb()
          }
        }catch(e){
          console.log(e)
        }

      })
    }
  }

  function putTips(){
    markList.length = 0;
    for(var i=0; i<carlist.length; i++){
      addMarker(carlist[i])
    }
  }

}


window.onload = initialize
