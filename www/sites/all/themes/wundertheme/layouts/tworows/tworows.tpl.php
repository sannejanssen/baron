<?php
/*
 * Custom panel layout
 */

// dsm($variables);

/*
$col_class = array();
$col_class[] = 'panel';

if(!$content['col_first'] || !$content['col_second']) {
  $col_class[] = 'single';
}
$css = 'class="' . implode(' ', $col_class) . '"';
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