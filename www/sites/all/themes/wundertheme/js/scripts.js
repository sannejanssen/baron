;(function($) {

  /* Mobile slidedown navigation */
  Drupal.behaviors.responsiveMainNav = {
    attach: function(context) {

      // NAVIGATION MENU
      var $navigation = $('.primary-navigation');
      var $navControl = $('#mobile-nav-control');
      var menuOpen = false;
      var navHtml = $navControl.html();

      // Disable control default link behavior
      $navControl.click(function(e) {
        e.preventDefault();
      });

      $navControl.bind('click', function(e) {
        if(!menuOpen) {
          $navigation.find('.menu').addClass('open');
          $navControl.addClass('open');
          $navigation.find('.menu').slideDown();
          $navControl.html(Drupal.t('Close'));
          menuOpen = true;
        }
        else {
          $navigation.find('.menu').removeClass('open');
          $navControl.removeClass('open');
          $navigation.find('.menu').slideUp();
          $navControl.html(navHtml);
          menuOpen = false;
        }

      });


    }
  };

})(jQuery);