/**
 * @file
 * Javascript functionality for the Thomas more site.
 */

(function ($) {

  Drupal.ThomasMore = Drupal.ThomasMore || {};

  $(document).ready(function(){
    // Resize the window to have a perfect ratio in the popup colorbox.
    // We unbind the end to avoid multiple fires that happen for an unknown reason.
    $(document).bind('cbox_complete', function(e) {
      // Don't do this for colorbox links with a fixed width and height.
      if (!$($.colorbox.element()).hasClass('facility-popup')) {
        Drupal.ThomasMore.popupInit();        
      }
      $(document).unbind('cbox_complete');
    });

    // Testimonials scroller for homepage.
    if ($('#testimonials-wrapper').length > 0) {
      var $wrapper = $('#testimonials-wrapper');
      var $list = $('.inner', $wrapper);
      var $prev = $('.prev', $wrapper);
      var $next = $('.next', $wrapper);

      var currentPosition = 1;
      var totalitems = $list.children().length;
      var displayItems = 2;
      var $items = $list.children();

      if(totalitems > displayItems) {
        // Init.
        if(currentPosition == 1 && totalitems > displayItems) {
          var name = $($items[parseInt(currentPosition + displayItems - 1)]).find('h3').html();
          $next.html('<span class="label">' + name + '</span>');
        }

        $next.click(function() {
          if ( !$next.hasClass('inactive')) {
            currentPosition++;
            // Label button 'previous'.
            if(currentPosition < totalitems) {
              var prevName = $($items[parseInt(currentPosition - displayItems)]).find('h3').html();
              $prev.html('<span class="label">' + prevName + '</span>');
            }

            // Label button 'next'.
            if(currentPosition+1 < totalitems) {
              var nextName = $($items[parseInt(currentPosition + displayItems -1)]).find('h3').html();
              $next.html('<span class="label">' + nextName + '</span>');
            } else {
              // No more items in the list.
              $next.addClass('inactive');
              $next.html('');
            }
          }
        });

        $prev.click(function() {
          if ( !$prev.hasClass('inactive')) {
            currentPosition--;
            if(currentPosition > 0) {

              // Label button 'next'.
              var nextName = $($items[parseInt(currentPosition + displayItems -1)]).find('h3').html();
              $next.html('<span class="label">' + nextName + '</span>');

              // No previous items
              if(currentPosition == 1) {
                $prev.html('');
                $prev.addClass('inactive');
              }

              if(currentPosition > 1) {
                // Label button 'previous'.
                var prevName = $($items[parseInt(currentPosition -2)]).find('h3').html();
                $prev.html('<span class="label">' + prevName + '</span>');
              }
            }
          }
        });
      }
      Drupal.ThomasMore.slideshow($('#testimonials-wrapper'));
    }
    
  });


  /*
   * Initialize all the required behaviors for the popup.
   */
  Drupal.ThomasMore.popupInit = function () {
    Drupal.ThomasMore.resizePopup();
    Drupal.ThomasMore.scrollThumbs();
    Drupal.ThomasMore.resizeVideo();
    Drupal.ThomasMore.bindClicks();
  }

  /*
   * Calculate the optimal width and height of popup
   * Make it as big as possible, but keep the correct ratio.
   */
  Drupal.ThomasMore.resizePopup = function () {
    var maxHeight = 762;
    var maxWidth = 978;
    var boxWidth = Math.round($(window).width() * 0.98);
    var boxHeight = Math.round($(window).height() * 0.98);

    var ratio = 1.50628930; // 958 / 715.

    if (boxWidth > boxHeight) {
      // Make sure the popup box does not become bigger than required for the 
      // Popup_full image style

      if (boxHeight > maxHeight) {
        boxHeight = maxHeight;
      } 
      boxWidth = Math.round((boxHeight - 109) * ratio); // 109 = body padding + thumbnail height.
      $.colorbox.resize({
        height: boxHeight,
        width: boxWidth
      });
    }
    if (boxWidth < boxHeight) {
      // Make sure the popup box does not become bigger than required for the 
      // Popup_full image style
      if (boxWidth > maxWidth) {
        boxWidth = maxWidth;
      } 
      boxHeight = Math.round((boxWidth / ratio) + 109); // 109 = body padding + thumbnail height.
      $.colorbox.resize({
        height: boxHeight,
        width: boxWidth
      });
    }
    // Add the size on the popup-content region so that it can be used for the video resizing.
    $('#popup-content').height(boxHeight - 109 - 17);

    // Resize the width of the thumbnail window so that the thumbs fit nicely.
    thumbWidth = $($('#popup-thumbs-wrapper .file')[0]).outerWidth();
    maxThumbs = Math.floor($('#popup-thumbs-wrapper .window').outerWidth() / thumbWidth);
    $('#popup-thumbs-wrapper .window').width(maxThumbs * thumbWidth).css('margin', '0 auto');
    
    // When closing the popup, we need to rebind again.
    $(document).bind('cbox_closed', function(e) {
      $(document).bind('cbox_complete', function(e) {
        Drupal.ThomasMore.popupInit();
        $(document).unbind('cbox_complete');
      });
      $(document).unbind('cbox_closed');
    });
  };

  /*
   * Make an ajax call for every thumbnail link.
   */
  Drupal.ThomasMore.bindClicks = function () {
    if ($('.lightbox-ajax').length > 0) {
      $('.lightbox-ajax').click(function() {

        // Get params from the class.
        var params = $(this).attr('href').split('/');

        $.ajax({
          type: 'GET',
          url: Drupal.settings.basePath + 'media/lightbox/ajax/' + params[3] + '/' + params[4],
          data: {},
          dataType: 'json',
          success: function (data) {
            if (data.status) {
              wrapper = $('#popup-content');
              Drupal.theme('ThomasMoreLightBoxDetail', wrapper, data.content);
              Drupal.ThomasMore.resizeVideo();
              Drupal.attachBehaviors();
            }
            else {
              alert('Er ging iets fout bij het opvragen van de data.');
            }
          },
          error: function (xmlhttp) {
            alert(Drupal.t('An HTTP error @status occurred.', {'@status': xmlhttp.status}));
          }
        });
        return false;
      });
    }
  }

  /*
   *  Resize the video iframe if necessary.
   */
  Drupal.ThomasMore.resizeVideo = function () {
    if ($('#popup-content .file-video').length > 0) {
      $width = Math.round($('#popup-content').innerWidth() - 20); // Keep the padding into account.
      $height = Math.round($('#popup-content').innerHeight() - 10); // Keep the padding into account.
      $('#popup-content .file-video iframe').attr('width', $width).attr('height', $height);
    }
  }

  /*
   *  Add scroll buttons to the thumbnails if necessary.
   */
  Drupal.ThomasMore.scrollThumbs = function () {// Popup animation.
    $wrapper = $('#popup-thumbs-wrapper');
    $list = $('.inner', $wrapper);
    $window = $('.window', $wrapper);
    if ($wrapper.length > 0) {
      
      // Add an active class on the active thumbnail.
      $('a', $wrapper).click(function() {
        var $el = $(this);
        if (!$el.hasClass('active')) {
          $('.active', $wrapper).removeClass('active');
          $el.addClass('active');
        }
      });
      
      // Make sure the active thumb is visible.
      if ($list.width > $window.width()) {
        activePosition = $('a.active', $wrapper).parent().position();
        $list.css('left', '-' + activePosition.left + 'px');
      }
      
      // Load the content when the prev/next arrows are clicked.
      $prev = $('.prev', $wrapper);
      $next = $('.next', $wrapper);
      $next.click(function() {
        $('a.active', $list).parent().next().children('a').click();
      });
      $prev.click(function() {
        $('a.active', $list).parent().prev().children('a').click();
      });

      // Add scrolling animation.
      Drupal.ThomasMore.slideshow($('#popup-thumbs-wrapper'));
    }
  }

  /**
   * Theme function for a replacing content of lightbox detail element.
   *
   * @param wrapper
   *   The HTML object which needs to be replaced
   * @param content
   *   The new content
   */
  Drupal.theme.prototype.ThomasMoreLightBoxDetail = function (wrapper, content) {
    wrapper.html(content);
  };

  /**
   * Custom slideshow function.
   * This function requires this HTML:
   *  #wrapper (parameter)
   *    .window
   *     .inner
   *   .prev
   *   .next
   */
  Drupal.ThomasMore.slideshow = function($wrapper) {
    var $window = $('.window', $wrapper);
    var $list = $('.inner', $wrapper);
    var $slide = $list.children();//$('.slide', $wrapper);
    var $prev = $('.prev', $wrapper);
    var $next = $('.next', $wrapper);
    var step = $($slide[0]).outerWidth();

    var listWidth = 0;
    $slide.each(function(index) {
      listWidth += step;
    });

    if (listWidth > $window.width()) {
      $list.width(listWidth);
      $next.removeClass('inactive');

      var doPrev = true;
      var doNext = true;
      $prev.bind('click', function() {
        if (doPrev) {
          if (parseInt($list.css('left')) < 0) {
            $next.removeClass('inactive');
            $list.animate({'left': parseInt($list.css('left')) + step}, function () {
              doPrev = true;
              // Make the 'prev' arrow inactive;
              if (parseInt($list.css('left'))== 0) {
                $prev.addClass('inactive');
              }
            });
          }
          else {
            doPrev = true;
          }
        }
      });
      $next.bind('click', function() {
        if (doNext) {
          doNext = false;
          if ($list.width() + parseInt($list.css('left')) - step >= $window.width()) {
            $prev.removeClass('inactive');
            $list.animate({'left': parseInt($list.css('left')) - step}, function () {
              doNext = true;
              // Make the 'next' arrow inactive;
              if (-parseInt($list.css('left')) + $window.width() == listWidth) {
                $next.addClass('inactive');
              }
            });
          }
          else {
            doNext = true;
          }
        }
      });
    }
  }
  
  /* Add a throbber to the search filters */
  Drupal.behaviors.filterThrobber  = {
    attach : function(context) {
      $('.search-filter a').click(function() {
        $container = $(this).parents('.row-search-filters');
        $throbber = '<div class="ajax-throbber" style="height:' + $container.height() +'px"></div>';
        $container.append($throbber);
      });
    }
  }

  
})(jQuery);
