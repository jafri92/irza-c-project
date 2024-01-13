#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>
#include <stdio.h>

typedef struct {
    double temperature;
    int humidity;
    double windSpeed;
} WeatherData;
struct string {
  char *ptr;
  size_t len;
};

void init_string(struct string *s) {
  s->len = 0;
  s->ptr = malloc(s->len + 1);
  if (s->ptr == NULL) {
    fprintf(stderr, "malloc() failed\n");
    exit(EXIT_FAILURE);
  }
  s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
  size_t new_len = s->len + size * nmemb;
  s->ptr = realloc(s->ptr, new_len + 1);
  if (s->ptr == NULL) {
    fprintf(stderr, "realloc() failed\n");
    exit(EXIT_FAILURE);
  }
  memcpy(s->ptr + s->len, ptr, size * nmemb);
  s->ptr[new_len] = '\0';
  s->len = new_len;

  return size * nmemb;
}

char* fetchWeatherData(const char* apiKey, const char* city) {
    CURL *curl;
    CURLcode res;
    struct string s;
    init_string(&s);

    char apiUrl[256];
    sprintf(apiUrl, "http://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s&units=metric", city, apiKey);

    curl = curl_easy_init();
    if(curl) {
        curl_easy_setopt(curl, CURLOPT_URL, apiUrl);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);

        if(res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            free(s.ptr);
            return NULL;
        }
    }

    return s.ptr;
}

WeatherData parseWeatherData(const char* jsonData) {
    WeatherData data = {0};
    struct json_object *parsed_json, *main, *temp, *humidity, *wind, *wind_speed;

    parsed_json = json_tokener_parse(jsonData);
    json_object_object_get_ex(parsed_json, "main", &main);
    json_object_object_get_ex(main, "temp", &temp);
    json_object_object_get_ex(main, "humidity", &humidity);
    json_object_object_get_ex(parsed_json, "wind", &wind);
    json_object_object_get_ex(wind, "speed", &wind_speed);

    data.temperature = json_object_get_double(temp);
    data.humidity = json_object_get_int(humidity);
    data.windSpeed = json_object_get_double(wind_speed);
    json_object_put(parsed_json); // Free memory

    return data;
}


// Function to check for temperature anomaly
int isTemperatureAnomaly(WeatherData data, double lowerThreshold, double upperThreshold) {
    if (data.temperature < lowerThreshold || data.temperature > upperThreshold) {
        return 1; // Anomaly detected
    }
    return 0; // No anomaly
}

int main() {
    const char* apiKey = "ENTER API KEY"; // Replace with your actual API key
    const char* city = "London"; // Replace with your desired city

    char* jsonData = fetchWeatherData(apiKey, city);
    if (jsonData != NULL) {
        WeatherData weatherData = parseWeatherData(jsonData);
        // Print the fetched weather data
        printf("Weather Data for %s:\n", city);
        printf("Temperature: %.2f°C\n", weatherData.temperature);
        printf("Humidity: %d%%\n", weatherData.humidity);
        printf("Wind Speed: %.2f m/s\n", weatherData.windSpeed);

        // Define your anomaly thresholds (example values)
        double lowerThreshold = 5.0; // Example lower threshold
        double upperThreshold = 35.0;  // Example upper threshold

        if (isTemperatureAnomaly(weatherData, lowerThreshold, upperThreshold)) {
            printf("Temperature anomaly detected!\n");
        } else {
            printf("No temperature anomaly detected.\n");
        }

        free(jsonData); // Free the JSON data
    } else {
        printf("Error fetching weather data\n");
    }

    return 0;
}
