;(function($) {

  /* Mobile slidedown navigation */
  Drupal.behaviors.responsiveMainNav = {
    attach: function(context) {

      // NAVIGATION MENU
      var $navigation = $('.primary-navigation');
      var $navControl = $('#mobile-nav-control');
      var menuOpen = false;

      // Disable control default link behavior
      $navControl.click(function(e) {
        e.preventDefault();
      });

      $navControl.bind('click', function(e) {
        if(!menuOpen) {
          $navigation.find('.menu').addClass('open');
          $navigation.find('.menu').slideDown();
          menuOpen = true;
        }
        else {
          $navigation.find('.menu').removeClass('open');
          $navigation.find('.menu').slideUp();
          menuOpen = false;
        }

      });


    }
  };

})(jQuery);