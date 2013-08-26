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


  /* Event body expander */
  Drupal.behaviors.expandableContent = {
    attach: function(context) {
      $('.event-body').expander({
        slicePoint:       120,  // default is 100
        expandPrefix:     ' ', // default is '... '
        expandText:       Drupal.t('read-more'), // default is 'read more'
        collapseTimer:    5000, // re-collapses after 5 seconds; default is 0, so no re-collapsing
        userCollapseText: '[^]',  // default is 'read less'
        expandEffect: 'slideDown',
        collapseEffect: 'slideUp'
      });
    }
  };

})(jQuery);