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
  'form callback' => 'geocomplete_location_input_geocomplete_form',
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

/**
 * Provides a configuration form for this location input plugin.
 *
 * @param array $form_state
 *   The form state data.
 *
 * @return array
 *   A form array for configuring this location input plugin.
 */
function geocomplete_location_input_geocomplete_form(array &$form_state, array $options) {
  $form = array();

  $options += array(
    'additional_types_container' => array(
      'additional_types' => array(),
    ),
  );

  $types = array(
    'street_address',
    'route',
    'intersection',
    'political',
    'country',
    'country_short',
    'administrative_area_level_1',
    'administrative_area_level_2',
    'administrative_area_level_3',
    'colloquial_area',
    'locality',
    'sublocality',
    'neighborhood',
    'premise',
    'subpremise',
    'postal_code',
    'natural_feature',
    'airport',
    'park',
    'point_of_interest',
    'post_box',
    'street_number',
    'floor',
    'room',
    'viewport',
    'location',
    'formatted_address',
    'location_type',
    'bounds',
  );

  $types_options = array();
  foreach ($types as $type) {
    $types_options[$type] = ucfirst(str_replace('_', ' ', $type));
  }

  $form['additional_types_container'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Additional info'),
    '#description' => t('<p>Geocomplete can collect additional info about the location besides latitude and longitude, like country or state.</p><p>The module does not use that info itself, but you may use it in other modules.</p>'),
  );
  $form['additional_types_container']['additional_types'] = array(
    '#type' => 'checkboxes',
    '#options' => $types_options,
    '#default_value' => $options['additional_types_container']['additional_types'],
  );

  return $form;
}
