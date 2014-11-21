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
      $("#edit-field-location-latlon").geocomplete();
      //$.fn.geocomplete("#edit-search-api-views-fulltext");

      // Trigger geocoding request.
      $("#edit-submit-location-search-kickstart").click(function(e){
        e.preventDefault();
        $("#edit-field-location-latlon").trigger("geocode");
      });
    }
  };

})(jQuery, Drupal, this, this.document);