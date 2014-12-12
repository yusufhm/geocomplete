/**
 * @file
 * A JavaScript file for the Geocomplete module.
 */
(function ($, Drupal, window, document, undefined) {

  function geocomplet(input, options) {

    this.input = input;

    this.$input = $(input);
    this.$details = this.$input.parents('form').find('[data-geocomplete-src="' + $(this).attr('name') + '"]');

    this.options = options;

    this.geolocation = navigator.geolocation;

    this.geocoder = new google.maps.Geocoder();

    this.init();

  }

  // Initialize all parts of the plugin.
  $.extend(geocomplet.prototype, {
    init: function () {
      this.initGeocomplete();

      this.initReverseGeocode();

    },

    initGeocomplete: function () {
      this.$input.geocomplete({
        details: this.$details,
        detailsAttribute: "data-geocomplete-type"
      });
    },

    initReverseGeocode: function () {
      if (this.geolocation && this.$input.hasClass('geocomplete-geolocation')) {
        var $button = $('<div class="geocomplete-geolocation-button-wrapper"><a href="#" class="geocomplete-geolocation-button"' +
          ' data-geocomplete-name="' + $(this).attr('name') + '">' + this.options.geolocation.title + '</a></div>');
        this.$input.after($button);
        this.$button = $button;
        this.$msgArea = this.$input.parent().next('.geocomplete-geolocation-msg');

        $button.click($.proxy(this.onGeolocateClick, this));
      }
    },

    onGeolocateClick: function (e) {
      e.preventDefault();
      this.$msgArea.html('');
      this.$input.val('');
      this.geolocation.getCurrentPosition($.proxy(this.posSuccess, this), $.proxy(this.posError, this), {timeout: 60000});
    },

    posSuccess: function (position) {
      $(this).find('input').val('');
      this.$details.find('input[data-geocomplete-type="lat"]').val(position.coords.latitude);
      this.$details.find('input[data-geocomplete-type="lng"]').val(position.coords.longitude);

      this.$msgArea.html(this.options.geolocation.success.replace('[lat]', position.coords.latitude).replace('[lng]', position.coords.longitude));

      if (this.options.geolocation.reverse) {
        var latlng = new google.maps.LatLng(position.coords.latitude, position.coords.longitude);
        this.geocoder.geocode({'latLng': latlng}, $.proxy(this.onGeocode, this));
      }

    },

    onGeocode: function (results, status) {
      if (status == google.maps.GeocoderStatus.OK) {
        if (results[1]) {
          this.$input.val(results[1].formatted_address);
        }
      }
    },

    posError: function () {
      this.$msgArea.after(this.options.geolocation.error);
    }
  });

  Drupal.behaviors.geocomplete = {
    attach: function (context, settings) {

      $('.geocomplete-input').each(function () {
        var instance = new geocomplet(this, settings.geocomplete[$(this).attr('data-geocomplete-hash')]);
      });

    }
  }

})(jQuery, Drupal, this, this.document);
