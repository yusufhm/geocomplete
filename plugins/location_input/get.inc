<?php

/**
 * @file
 * Plugin to provide raw location input.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Input from latlon GET parameter'),
  'description' => t(''),
  'input callback' => 'geocomplete_location_input_get',
);

/**
 * Returns the data exactly as entered.
 *
 * @param $input
 *   The text entered by the user.
 * @param array $options
 *   The options for this plugin (empty).
 *
 * @return
 *   $input if it is a valid location string. NULL otherwise.
 */
function geocomplete_location_input_get($input, array $options) {
  $locality = geocomplete_locality_geocode($input);
  return isset($locality['latlon']) ? $locality['latlon'] : NULL;
}

/**
 * Stores calculated geocodes.
 */
function geocomplete_locality_geocode($address) {
  $address = trim($address);
  if (isset($_GET['place']) && trim($_GET['place']) == $address && isset($_GET['latlon'])) {
    if (empty($_GET['latlon'])) $_GET['latlon'] = '0.1,0.1';
    list($lat, $lon) = explode(',', trim($_GET['latlon']));
    $addresses[$address] = array(
      'latlon' => $lat . ',' . $lon,
      'lat' => $lat,
      'lon' => $lon,
      'suburb' => isset($_GET['suburb']) ? trim($_GET['suburb']) : NULL,
      'postcode' => isset($_GET['postcode']) ? trim($_GET['postcode']) : NULL,
      'council' => isset($_GET['council']) ? trim($_GET['council']) : NULL,
    );
  }
  else {
    watchdog('Geocoding', 'Request to google geocoder');
    $location = geocoder('google', trim($address));
    if ($location) {
      $location = $location->centroid();
      $lat = $location->y();
      $lon = $location->x();
      $suburb = NULL;
      $postcode = NULL;
      if (!empty($location->data['geocoder_address_components'])) {
        foreach ($location->data['geocoder_address_components'] as $component) {
          if (in_array('locality', $component->types)) {
            $suburb = $component->long_name;
          }
          if (in_array('postal_code', $component->types)) {
            $postcode = $component->long_name;
          }
        }
      }
      $addresses[$address] = array(
        'latlon' => $lat . ',' . $lon,
        'lat' => $lat,
        'lon' => $lon,
        'suburb' => $suburb,
        'postcode' => $postcode,
      );
    }
    else {
      return array(
        'latlon' => '0.1,0.1',
        'lat' => 0.1,
        'lon' => 0.1,
        'suburb' => '',
        'postcode' => '',
      );
    }
  }
  return isset($addresses[$address]) ? $addresses[$address] : NULL;
}