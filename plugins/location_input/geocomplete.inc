<?php

/**
 * @file
 * Plugin to provide Geocomplete location input.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('Geocomplete'),
  'description' => t('Provides input with client-side autocomplete geocoding.'),
  'input callback' => 'geocomplete_location_input_geocomplete',
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
function geocomplete_location_input_geocomplete($input, array $options) {
  $latlon = NULL;
  $view = views_get_current_view();
  $data = $view->exposed_data;
  foreach ($data as $key => $value) {
    if ($value == $input && isset($data[$key . '_lat']) && isset($data[$key . '_lng'])) {
      $latlon = $data[$key . '_lat'] . ',' . $data[$key . '_lng'];
      break;
    }
  }
  return $latlon;
}
