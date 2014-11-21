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
  'title' => t('Geocomplete'),
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
  if (empty($_GET['lat'])) $_GET['lat'] = '0.1';
  if (empty($_GET['lng'])) $_GET['lng'] = '0.1';
  $lat = $_GET['lat'];
  $lon = $_GET['lng'];
  $coordinates = array(
    'latlon' => $lat . ',' . $lon,
    'lat' => $lat,
    'lon' => $lon
  );
  return isset($coordinates['latlon']) ? $coordinates['latlon'] : NULL;
}