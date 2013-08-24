(function ($) {

  Drupal.ThomasMore = Drupal.ThomasMore || {};
  
  $(document).ready(function () {

    var displaylimit = 20;
    var twitterprofile = "ThomasMoreBE";
    var showdirecttweets = false;
    var showretweets = true;
     
    var loadingHTML = '';
    loadingHTML += '<div id="loading-container"><img src="/sites/all/themes/wundertheme/images/ajax-loader.gif" width="32" height="32" alt="tweet loader" /></div>';
     
    $('#twitter-feed-wrapper .inner').html(loadingHTML);

    $.getJSON('/sites/all/modules/custom/thomas_more/includes/twitter_feed.php',
        function(feeds) {  
            //alert(feeds);
            var feedHTML = '';
            var metaHTML = '';
            var displayCounter = 1; 
            var extraClass = '';
            for (var i=0; i<feeds.length; i++) {
                var tweetscreenname = feeds[i].user.name;
                var tweetusername = feeds[i].user.screen_name;
                var profileimage = feeds[i].user.profile_image_url_https;
                var status = feeds[i].text;
                var isaretweet = false;
                var isdirect = false;
                var tweetid = feeds[i].id_str;
                 
                //If the tweet has been retweeted, get the profile pic of the tweeter
                if(typeof feeds[i].retweeted_status != 'undefined'){
                   profileimage = feeds[i].retweeted_status.user.profile_image_url_https;
                   tweetscreenname = feeds[i].retweeted_status.user.name;
                   tweetusername = feeds[i].retweeted_status.user.screen_name;
                   tweetid = feeds[i].retweeted_status.id_str
                   isaretweet = true;
                 };
                  
                  
                 //Check to see if the tweet is a direct message
                 if (feeds[i].text.substr(0,1) == "@") {
                     isdirect = true;
                 }
                  
                 if (((showretweets == true) || ((isaretweet == false) && (showretweets == false))) && ((showdirecttweets == true) || ((showdirecttweets == false) && (isdirect == false)))) {
                    if ((feeds[i].text.length > 1) && (displayCounter <= displaylimit)) {  
                      feedHTML += '<div class="twitter-article">';                 
                      feedHTML += '<div class="twitter-text"><p>'+ replaceURLWithHTMLLinks(status) +'</p></div>';
                      feedHTML += '</div>';
                      
                      if (displayCounter == 1) {
                        extraClass = ' active';
                      }
                      else {
                        extraClass = '';
                      }
                      metaHTML += '<div class="meta'+ extraClass + '"><a href="https://twitter.com/'+tweetusername+'" >@'+tweetusername+'</a><br />'+relative_time(feeds[i].created_at)+'</div>';
                      displayCounter++;
                    }  
                 }
            }
              
            $('#twitter-feed-wrapper .inner').html(feedHTML);
            $('#twitter-feed-meta').prepend(metaHTML);
            scroll_tweets();
            // Fade in all content
            $('.twitter-article, #twitter-feed-meta').fadeIn();
    });
        
  });
  
  /*
   *  Convert time to relative time, twitter style.
   */
  function relative_time(time_value) {
    var values = time_value.split(" ");
    time_value = values[1] + " " + values[2] + ", " + values[5] + " " + values[3];
    var parsed_date = Date.parse(time_value);
    var relative_to = (arguments.length > 1) ? arguments[1] : new Date();
    var delta = parseInt((relative_to.getTime() - parsed_date) / 1000);
    var shortdate = time_value.substr(4,2) + " " + time_value.substr(0,3);
    delta = delta + (relative_to.getTimezoneOffset() * 60);
    
    if (delta < 60) {
      return '1m';
    } else if(delta < 120) {
      return '1m';
    } else if(delta < (60*60)) {
      return (parseInt(delta / 60)).toString() + 'm';
    } else if(delta < (120*60)) {
      return '1h';
    } else if(delta < (24*60*60)) {
      return (parseInt(delta / 3600)).toString() + 'h';
    } else if(delta < (48*60*60)) {
      //return '1 day';
      return shortdate;
    } else {
      return shortdate;
    }
  }
  
  /*
   *  Add scroll buttons to the tweets.
   */
  function scroll_tweets() {
    if ($('#twitter-feed-wrapper').length > 0) {
      var $wrapper = $('#twitter-feed-wrapper');
      
      // Add fade effect for meta information.
      var $prev = $('.prev', $wrapper);
      var $next = $('.next', $wrapper);
      $prev.click(function() {
        if (!$(this).hasClass('inactive')) {
          $('.meta.active').removeClass('active').fadeOut().prev().fadeIn().addClass('active');
        }
      });
      $next.click(function() {
        if (!$(this).hasClass('inactive')) {
          $('.meta.active').removeClass('active').fadeOut().next().fadeIn().addClass('active');
        }
      });
      
      // Add scrolling animation.
      Drupal.ThomasMore.slideshow($wrapper);
    }
  }  
  
  /*
   *  Convert urls to clickable links.
   */
  function replaceURLWithHTMLLinks(text) {
    var exp = /(\b(https?|ftp|file):\/\/[-A-Z0-9+&@#\/%?=~_|!:,.;]*[-A-Z0-9+&@#\/%=~_|])/ig;
    return text.replace(exp,'<a target="_blank" href="$1">$1</a>'); 
  }
  
})(jQuery);