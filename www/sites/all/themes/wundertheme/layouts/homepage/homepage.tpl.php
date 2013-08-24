<?php
/*
 * Custom panel layout
 */
?>

<div class="homepage">

  <?php if($content['row_events']): ?>
    <div class="row events">
      <div class="container">
        <?php print $content['row_events']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if($content['row_social']): ?>
    <div class="row social-blocks">
      <div class="container">
        <?php print $content['row_social']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if($content['row_pictures']): ?>
    <div class="row pictures">
      <div class="container">
        <?php print $content['row_pictures']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if($content['row_videos']): ?>
    <div class="row videos">
      <div class="container">
        <?php print $content['row_videos']; ?>
      </div>
    </div>
  <?php endif; ?>

  <?php if($content['row_contact']): ?>
    <div class="row contact">
      <div class="container">
        <?php print $content['row_contact']; ?>
      </div>
    </div>
  <?php endif; ?>

</div> <!-- end homepage//-->
