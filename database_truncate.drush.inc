<?php
/**
 *@File This command is for truncating any large db
 *
 */

/**
 * Implements hook_drush_command().
 */
function database_truncate_drush_command() {
  $items = array();

  $items['database-truncate'] = array(
    'description' => "Delete nodes that are older than 30 days",
    'examples' => array(
      'drush dbtrunc' => 'Delete the nodes',
    ),
    'aliases' => array('dbtrunc'),
    'bootstrap' => DRUSH_BOOTSTRAP_MAX,
  );
  return $items;
}

/**
 * Updates a role.
 */
function drush_database_truncate() {
  // I want to revisit this
  if (db_table_exists('comment')) {
   $query = db_query("DELETE FROM comment WHERE status = 0");
  }
  if (db_table_exists('field_revision_field_issue_changes')) {
   $query = db_query("DELETE FROM field_revision_field_issue_changes");
  }
  if (db_table_exists('field_data_field_issue_changes')) {
   $query = db_query("DELETE FROM field_data_field_issue_changes");
  }
  $query = db_query('SELECT nid FROM node WHERE FROM_UNIXTIME(created) > NOW() - INTERVAL 80 DAY');
  while ($result = $query->fetch()) {
    node_delete($result->nid);
  }
}
