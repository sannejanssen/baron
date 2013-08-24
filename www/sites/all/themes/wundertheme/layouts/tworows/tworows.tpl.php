<?php
/*
 * Custom panel layout
 */
?>

<?php if($content['row_one']): ?>
  <div class="row-one">
    <?php print $content['row_one']; ?>
  </div>
<?php endif; ?>

<?php if($content['row_two']): ?>
  <div class="container">
    <div class="row-two"><?php print $content['row_two']; ?></div>
  </div>
<?php endif; ?>