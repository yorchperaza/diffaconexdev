/**
 * JS for ACX module.
 */
(function($) {

  Drupal.behaviors.projectFilters = {
    attach: function() {
      var $view = $('.view-projects');
      var $document = $(document);

      var $form = $('#acx-project-form');
      var $exposedForm = $('#views-exposed-form-projects-projects');

      if ($form.length) {
        var $regionField = $form.find('[name="field_region"]');
        var $industryField = $form.find('[name="field_industry"]');
        var $regionExposed = $exposedForm.find('[name="region"]');
        var $industryExposed = $exposedForm.find('[name="industry"]');

        // Submit the form when the filter changes.
        $form.find('select').on('change', function() {
          $regionExposed.val($regionField.val());
          $industryExposed.val($industryField.val()).trigger('change');
        });

        $document.ajaxStart(function () {
          $view.addClass('loading');
        });

        $document.ajaxStop(function () {
          $view.removeClass('loading');
        });
      }
    }
  };

})(jQuery);