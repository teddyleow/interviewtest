package com.example;

import org.apache.http.HttpResponse;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.HttpClientBuilder;
import org.apache.http.util.EntityUtils;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import com.alibaba.fastjson.JSON;
import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;


@RestController
public class DemoController {
	
	
	private static final HttpClient httpClient = HttpClientBuilder.create().build();
	
	
	@RequestMapping(value = "/location", method = RequestMethod.GET)
	public String  getLocation(@RequestParam("bounds") String locationString ) throws Exception {
		JSONArray jsonarray = JSON.parseArray(locationString);
		if(jsonarray.size() != 2){
			return "";
		}
		JSONArray A=JSON.parseArray(jsonarray.get(0).toString());
		JSONArray B=JSON.parseArray(jsonarray.get(1).toString());
		if(A.size() != 2 || B.size() != 2){
			return "";
		}
		Double longitudeMin=A.getDoubleValue(0);
		Double longitudeMax=B.getDoubleValue(0);
		Double latitudeMin=B.getDoubleValue(1);
		Double latitudeMax=A.getDoubleValue(1);
		
		String locationList = location(longitudeMin,longitudeMax,latitudeMin,latitudeMax);
		return locationList;
	}

	public boolean isHere(double longitudeMin, double longitudeMax, double latitudeMin, double latitudeMax, double longitude,
			double latitude) {
		return longitudeMin <= longitude && longitude <= longitudeMax && latitudeMin <= latitude
				&& latitude <= latitudeMax;

	}

	public String location(double longitudeMin, double longitudeMax, double latitudeMin, double latitudeMax) throws Exception {
		HttpGet get = new HttpGet("https://data.sfgov.org/resource/6a9r-agq8.json");
		HttpResponse response = httpClient.execute(get);
		int code = response.getStatusLine().getStatusCode();
		JSONArray newarry = new JSONArray();
		if (code == 200) {
			String content = EntityUtils.toString(response.getEntity());

			JSONArray jsonarray = JSON.parseArray(content);
			
			for (int i = 0; i < jsonarray.size(); i++) {
				JSONObject jsonObject = JSON.parseObject(jsonarray.get(i).toString());
				JSONObject location = new JSONObject();
				Double longitude=Double.valueOf(jsonObject.get("longitude").toString());
				Double latitude=Double.valueOf(jsonObject.get("latitude").toString());			
				if(isHere(longitudeMin,longitudeMax,latitudeMin,latitudeMax,longitude,latitude)){
				location.put("location", jsonObject.get("location"));
				newarry.add(location);
				}
			}
			
		}
		return newarry.toJSONString();
	}
}
