/**
 * @file
 * A JavaScript file for the theme.
 */

// JavaScript should be made compatible with libraries other than jQuery by
// wrapping it with an "anonymous closure". See:
// - https://drupal.org/node/1446420
// - http://www.adequatelygood.com/2010/3/JavaScript-Module-Pattern-In-Depth
(function ($, Drupal, window, document, undefined) {

  Drupal.behaviors.geo = {
    attach: function (context, settings) {

      var $form_field_geocomplete = $("#" + Drupal.settings.geocomplete.form_field_geocomplete),
          $form_field_submit      = $("#" + Drupal.settings.geocomplete.form_field_submit);

      $form_field_geocomplete.geocomplete({ details: "form" });

      // Trigger geocoding request.
      $form_field_submit.click(function(e){
        $form_field_geocomplete.trigger("geocode");
      });
    }
  };

})(jQuery, Drupal, this, this.document);