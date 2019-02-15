<?php

function register_user($form_state) {
    $name = $form_state['values']['user_name'];
    $email= $form_state['values']['user_email'];
    $type = $form_state['complete form']['user_type']['#options'][$form_state['values']['user_type']];
    $password = md5($form_state['values']['user_password']);
  
    $url = 'http://localhost:5000/api/users'; //URL API

    $data = array(
        'name' => $name,
        'email' => $email,
        'type' => $type,
        'password' => $password
    );
  
    $options = array(
      'method' => "POST",
      'data' => json_encode($data),
      'headers' => array(
        'Content-Type' => "application/json", //Identifying the content type
        'cache-control' => "no-cache")
    );
    $request = drupal_http_request($url, $options);
    if (get_result($request)) {
        return $request;
    }
}
  
function delete_user($id) {
    $url = 'http://localhost:5000/api/users/'.$id; //URL API

    $options = array(
        'method' => "DELETE",
        'data' => "",
        'headers' => array(
        'Content-Type' => "application/json", //Identifying the content type
        'cache-control' => "no-cache")
    );
    $request = drupal_http_request($url, $options);
    if (get_result($request)) {
        return $request;
    }
}

function user_search($name) {
    $url = 'http://localhost:5000/api/users?q='.$name; //URL API
    
    $options = array(
        'method' => "GET",
        'data' => "",
        'headers' => array(
        'Content-Type' => "application/json", //Identifying the content type
        'cache-control' => "no-cache")
    );
    $request = drupal_http_request($url, $options);
    if (get_result($request)) {
        return $request;
    }
}

function get_all_users() {
    $url = 'http://localhost:5000/api/users'; //URL API
    $options = array(
        'method' => "GET",
        'data' => "",
        'headers' => array(
        'Content-Type' => "application/json", //Identifying the content type
        'cache-control' => "no-cache")
    );
    $request = drupal_http_request($url, $options);
    if (get_result($request)){
        return $request;
    }
}

function get_result($request) {
    //Checking if the API response has the 'data' parameter
    if (!isset($request->data)) {
        drupal_set_message(t("Nenhuma conexão foi estabelecida. Tente novamente mais tarde ou contate o administrador."), 'error');
        return FALSE;
    } else {
        return TRUE;
    } 
}
