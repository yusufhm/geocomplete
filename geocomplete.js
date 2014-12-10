/**
 * @file
 * A JavaScript file for the Geocomplete module.
 */
(function ($, Drupal, window, document, undefined) {

  Drupal.behaviors.geocomplete = {
    attach: function (context, settings) {

      // Process all gecocomplete inputs.
      var geolocation = navigator.geolocation;
      $('.geocomplete-input').each(function () {
        var $details = $(this).parents('form').find('[data-geocomplete-src="' + $(this).attr('name') + '"]');
        $(this).geocomplete({
          details: $details,
          detailsAttribute: "data-geocomplete-type"
        });

        var sets = settings.geocomplete[$(this).attr('data-geocomplete-hash')];
        $details.data({
          settings: sets,
          input: $(this)
        });

        // Add geolocation link.
        if (geolocation && $(this).hasClass('geocomplete-geolocation')) {
          var $button = $('<div class="geocomplete-geolocation-button-wrapper"><a href="#" class="geocomplete-geolocation-button"' +
            ' data-geocomplete-name="' + $(this).attr('name') + '">' + sets.geolocation.title + '</a></div>');
          $(this).after($button);
          $details.data('button', $button);
          $details.data('msgArea', $(this).parent().next('.geocomplete-geolocation-msg'));

        }
      });

      $('.geocomplete-geolocation-button').click(function (e) {
        e.preventDefault();
        $('.geocomplete-geolocation-msg').html('');
        $(this).parents('form').find('[data-geocomplete-src="' + $(this).attr('data-geocomplete-name') + '"]').addClass('geocomplete-geolocation-processing');
        geolocation.getCurrentPosition(posSuccess, posError, {timeout: 60000});
      });

      function posSuccess(position) {
        $('.geocomplete-geolocation-processing').each(function () {
          $(this).find('input').val('');
          $(this).find('input[data-geocomplete-type="lat"]').val(position.coords.latitude);
          $(this).find('input[data-geocomplete-type="lng"]').val(position.coords.longitude);
          $(this).removeClass('geocomplete-geolocation-processing');
          $(this).data('msgArea').html($(this).data('settings').geolocation.success.replace('[lat]', position.coords.latitude).replace('[lng]', position.coords.longitude));
        });
      }

      function posError(err) {
        $('.geocomplete-geolocation-processing').each(function () {
          $(this).removeClass('geocomplete-geolocation-processing');
          $(this).data('msgArea').after($(this).data('settings').geolocation.error);
        });
      }

    }
  };

})(jQuery, Drupal, this, this.document);