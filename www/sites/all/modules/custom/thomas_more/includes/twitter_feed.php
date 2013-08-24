<?php
  require_once('twitteroauth/twitteroauth/twitteroauth.php'); //Path to twitteroauth library

  $twitteruser = "ThomasMoreBE";
  $notweets = 20;
  $consumerkey = "zYvGLwmtzAhGCfs678zaQ";
  $consumersecret = "wkWx3dnAoDqfpi04JIkWB5D367KQjILVxnABmZksf5o";
  $accesstoken = "133653529-SzQEZ2bUPAyJqDJO3LYSWgxwzcCLoqNQX0EVeUyE";
  $accesstokensecret = "yKxsR8sCEiaryKl2hQIdI6Uq0cNCdYsj7nOm57Nrg";

  /* Actual ThomasMoreBE information:
    $twitteruser = "ThomasMoreBE";
    $notweets = 20;
    $consumerkey = "T0dWFhMxIFi3d1vp6iN0AQ";
    $consumersecret = "Ft3a9xhKGZn24jJuQHL9mNkfZyiOwVWHKNef7zrhP5s";
    $accesstoken = "957208351-JhgyW7fDBFLkoK3hkW8yGBevt4l0iOqDtq6pFQBh";
    $accesstokensecret = "wPyUwVuYU1D2jFNYirdjscx9TwOpu8NCz6YNF7uc";
   */
  function getConnectionWithAccessToken($cons_key, $cons_secret, $oauth_token, $oauth_token_secret) {
    $connection = new TwitterOAuth($cons_key, $cons_secret, $oauth_token, $oauth_token_secret);
    return $connection;
  }

  $connection = getConnectionWithAccessToken($consumerkey, $consumersecret, $accesstoken, $accesstokensecret);
  $tweets = $connection->get("https://api.twitter.com/1.1/statuses/user_timeline.json?screen_name=".$twitteruser."&count=".$notweets);

  echo json_encode($tweets);
?>
